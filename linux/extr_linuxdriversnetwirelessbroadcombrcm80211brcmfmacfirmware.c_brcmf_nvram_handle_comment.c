#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nvram_parser {size_t pos; int column; int /*<<< orphan*/  line; int /*<<< orphan*/ * data; } ;
typedef  enum nvram_parser_state { ____Placeholder_nvram_parser_state } nvram_parser_state ;

/* Variables and functions */
 int END ; 
 int IDLE ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static enum nvram_parser_state
brcmf_nvram_handle_comment(struct nvram_parser *nvp)
{
	char *eoc, *sol;

	sol = (char *)&nvp->data[nvp->pos];
	eoc = strchr(sol, '\n');
	if (!eoc) {
		eoc = strchr(sol, '\0');
		if (!eoc)
			return END;
	}

	/* eat all moving to next line */
	nvp->line++;
	nvp->column = 1;
	nvp->pos += (eoc - sol) + 1;
	return IDLE;
}