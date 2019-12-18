#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct symbol {int /*<<< orphan*/  start; int /*<<< orphan*/  end; } ;
struct map {int dummy; } ;
struct TYPE_10__ {void* addr; int offset_avail; TYPE_4__* sym; void* offset; } ;
struct TYPE_11__ {TYPE_2__ target; } ;
struct TYPE_15__ {scalar_t__ ops; } ;
struct disasm_line {int /*<<< orphan*/  al; TYPE_3__ ops; TYPE_8__ ins; } ;
struct annotation {TYPE_5__* src; } ;
struct TYPE_9__ {struct symbol* sym; struct map* map; } ;
struct annotate_args {int offset; char* line; int line_nr; TYPE_1__ ms; } ;
struct addr_map_symbol {void* addr; scalar_t__ al_addr; TYPE_4__* sym; struct map* map; } ;
typedef  int s64 ;
struct TYPE_14__ {int rm_so; } ;
typedef  TYPE_6__ regmatch_t ;
struct TYPE_13__ {int /*<<< orphan*/  source; } ;
struct TYPE_12__ {scalar_t__ start; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  annotation_line__add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  disasm_line__has_local_offset (struct disasm_line*) ; 
 struct disasm_line* disasm_line__new (struct annotate_args*) ; 
 int /*<<< orphan*/  file_lineno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ ins__is_call (TYPE_8__*) ; 
 void* map__rip_2objdump (struct map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_groups__find_ams (struct addr_map_symbol*) ; 
 scalar_t__ regexec (int /*<<< orphan*/ *,char*,int,TYPE_6__*,int /*<<< orphan*/ ) ; 
 char* skip_spaces (char*) ; 
 char* strim (char*) ; 
 int strtoull (char*,char**,int) ; 
 struct annotation* symbol__annotation (struct symbol*) ; 

__attribute__((used)) static int symbol__parse_objdump_line(struct symbol *sym, FILE *file,
				      struct annotate_args *args,
				      int *line_nr)
{
	struct map *map = args->ms.map;
	struct annotation *notes = symbol__annotation(sym);
	struct disasm_line *dl;
	char *line = NULL, *parsed_line, *tmp, *tmp2;
	size_t line_len;
	s64 line_ip, offset = -1;
	regmatch_t match[2];

	if (getline(&line, &line_len, file) < 0)
		return -1;

	if (!line)
		return -1;

	line_ip = -1;
	parsed_line = strim(line);

	/* /filename:linenr ? Save line number and ignore. */
	if (regexec(&file_lineno, parsed_line, 2, match, 0) == 0) {
		*line_nr = atoi(parsed_line + match[1].rm_so);
		return 0;
	}

	tmp = skip_spaces(parsed_line);
	if (*tmp) {
		/*
		 * Parse hexa addresses followed by ':'
		 */
		line_ip = strtoull(tmp, &tmp2, 16);
		if (*tmp2 != ':' || tmp == tmp2 || tmp2[1] == '\0')
			line_ip = -1;
	}

	if (line_ip != -1) {
		u64 start = map__rip_2objdump(map, sym->start),
		    end = map__rip_2objdump(map, sym->end);

		offset = line_ip - start;
		if ((u64)line_ip < start || (u64)line_ip >= end)
			offset = -1;
		else
			parsed_line = tmp2 + 1;
	}

	args->offset  = offset;
	args->line    = parsed_line;
	args->line_nr = *line_nr;
	args->ms.sym  = sym;

	dl = disasm_line__new(args);
	free(line);
	(*line_nr)++;

	if (dl == NULL)
		return -1;

	if (!disasm_line__has_local_offset(dl)) {
		dl->ops.target.offset = dl->ops.target.addr -
					map__rip_2objdump(map, sym->start);
		dl->ops.target.offset_avail = true;
	}

	/* kcore has no symbols, so add the call target symbol */
	if (dl->ins.ops && ins__is_call(&dl->ins) && !dl->ops.target.sym) {
		struct addr_map_symbol target = {
			.map = map,
			.addr = dl->ops.target.addr,
		};

		if (!map_groups__find_ams(&target) &&
		    target.sym->start == target.al_addr)
			dl->ops.target.sym = target.sym;
	}

	annotation_line__add(&dl->al, &notes->src->source);

	return 0;
}