#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {unsigned long pc; int /*<<< orphan*/  methodID; scalar_t__ discrim; int /*<<< orphan*/  line_number; } ;
typedef  TYPE_1__ jvmti_line_info_t ;
struct TYPE_11__ {size_t start_location; int /*<<< orphan*/  line_number; } ;
typedef  TYPE_2__ jvmtiLineNumberEntry ;
typedef  scalar_t__ jvmtiError ;
typedef  TYPE_3__* jvmtiEnv ;
typedef  int /*<<< orphan*/  jmethodID ;
typedef  size_t jint ;
struct TYPE_12__ {scalar_t__ (* GetLineNumberTable ) (TYPE_3__**,int /*<<< orphan*/ ,size_t*,TYPE_2__**) ;int /*<<< orphan*/  (* Deallocate ) (TYPE_3__**,unsigned char*) ;} ;

/* Variables and functions */
 scalar_t__ JVMTI_ERROR_NONE ; 
 int /*<<< orphan*/  print_error (TYPE_3__**,char*,scalar_t__) ; 
 scalar_t__ stub1 (TYPE_3__**,int /*<<< orphan*/ ,size_t*,TYPE_2__**) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__**,unsigned char*) ; 

__attribute__((used)) static jvmtiError
do_get_line_numbers(jvmtiEnv *jvmti, void *pc, jmethodID m, jint bci,
		    jvmti_line_info_t *tab, jint *nr)
{
	jint i, lines = 0;
	jint nr_lines = 0;
	jvmtiLineNumberEntry *loc_tab = NULL;
	jvmtiError ret;

	ret = (*jvmti)->GetLineNumberTable(jvmti, m, &nr_lines, &loc_tab);
	if (ret != JVMTI_ERROR_NONE) {
		print_error(jvmti, "GetLineNumberTable", ret);
		return ret;
	}

	for (i = 0; i < nr_lines; i++) {
		if (loc_tab[i].start_location < bci) {
			tab[lines].pc = (unsigned long)pc;
			tab[lines].line_number = loc_tab[i].line_number;
			tab[lines].discrim = 0; /* not yet used */
			tab[lines].methodID = m;
			lines++;
		} else {
			break;
		}
	}
	(*jvmti)->Deallocate(jvmti, (unsigned char *)loc_tab);
	*nr = lines;
	return JVMTI_ERROR_NONE;
}