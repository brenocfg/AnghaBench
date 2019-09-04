#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jvmti_line_info_t ;
typedef  int /*<<< orphan*/  jvmtiLineNumberEntry ;
typedef  scalar_t__ jvmtiError ;
typedef  TYPE_1__* jvmtiEnv ;
struct TYPE_11__ {scalar_t__ kind; struct TYPE_11__* next; } ;
typedef  TYPE_2__ jvmtiCompiledMethodLoadRecordHeader ;
struct TYPE_12__ {int numpcs; TYPE_4__* pcinfo; } ;
typedef  TYPE_3__ jvmtiCompiledMethodLoadInlineRecord ;
typedef  scalar_t__ jint ;
struct TYPE_13__ {int /*<<< orphan*/ * bcis; int /*<<< orphan*/ * methods; int /*<<< orphan*/  pc; } ;
struct TYPE_10__ {scalar_t__ (* GetLineNumberTable ) (TYPE_1__**,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ **) ;int /*<<< orphan*/  (* Deallocate ) (TYPE_1__**,unsigned char*) ;} ;
typedef  TYPE_4__ PCStackInfo ;

/* Variables and functions */
 scalar_t__ JVMTI_CMLR_INLINE_INFO ; 
 scalar_t__ JVMTI_ERROR_NONE ; 
 scalar_t__ JVMTI_ERROR_NOT_FOUND ; 
 scalar_t__ JVMTI_ERROR_NULL_POINTER ; 
 scalar_t__ JVMTI_ERROR_OUT_OF_MEMORY ; 
 scalar_t__ do_get_line_numbers (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  print_error (TYPE_1__**,char*,scalar_t__) ; 
 scalar_t__ stub1 (TYPE_1__**,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__**,unsigned char*) ; 

__attribute__((used)) static jvmtiError
get_line_numbers(jvmtiEnv *jvmti, const void *compile_info, jvmti_line_info_t **tab, int *nr_lines)
{
	const jvmtiCompiledMethodLoadRecordHeader *hdr;
	jvmtiCompiledMethodLoadInlineRecord *rec;
	jvmtiLineNumberEntry *lne = NULL;
	PCStackInfo *c;
	jint nr, ret;
	int nr_total = 0;
	int i, lines_total = 0;

	if (!(tab && nr_lines))
		return JVMTI_ERROR_NULL_POINTER;

	/*
	 * Phase 1 -- get the number of lines necessary
	 */
	for (hdr = compile_info; hdr != NULL; hdr = hdr->next) {
		if (hdr->kind == JVMTI_CMLR_INLINE_INFO) {
			rec = (jvmtiCompiledMethodLoadInlineRecord *)hdr;
			for (i = 0; i < rec->numpcs; i++) {
				c = rec->pcinfo + i;
				nr = 0;
				/*
				 * unfortunately, need a tab to get the number of lines!
				 */
				ret = (*jvmti)->GetLineNumberTable(jvmti, c->methods[0], &nr, &lne);
				if (ret == JVMTI_ERROR_NONE) {
					/* free what was allocated for nothing */
					(*jvmti)->Deallocate(jvmti, (unsigned char *)lne);
					nr_total += (int)nr;
				} else {
					print_error(jvmti, "GetLineNumberTable", ret);
				}
			}
		}
	}

	if (nr_total == 0)
		return JVMTI_ERROR_NOT_FOUND;

	/*
	 * Phase 2 -- allocate big enough line table
	 */
	*tab = malloc(nr_total * sizeof(**tab));
	if (!*tab)
		return JVMTI_ERROR_OUT_OF_MEMORY;

	for (hdr = compile_info; hdr != NULL; hdr = hdr->next) {
		if (hdr->kind == JVMTI_CMLR_INLINE_INFO) {
			rec = (jvmtiCompiledMethodLoadInlineRecord *)hdr;
			for (i = 0; i < rec->numpcs; i++) {
				c = rec->pcinfo + i;
				nr = 0;
				ret = do_get_line_numbers(jvmti, c->pc,
							  c->methods[0],
							  c->bcis[0],
							  *tab + lines_total,
							  &nr);
				if (ret == JVMTI_ERROR_NONE)
					lines_total += nr;
			}
		}
	}
	*nr_lines = lines_total;
	return JVMTI_ERROR_NONE;
}