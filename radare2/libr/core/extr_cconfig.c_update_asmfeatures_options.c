#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  (* free ) (char*) ;} ;
struct TYPE_11__ {TYPE_7__* options; } ;
struct TYPE_10__ {TYPE_2__* assembler; } ;
struct TYPE_9__ {TYPE_1__* cur; } ;
struct TYPE_8__ {char const* features; } ;
typedef  TYPE_3__ RCore ;
typedef  TYPE_4__ RConfigNode ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  r_list_append (TYPE_7__*,char*) ; 
 int r_str_split (char*,char) ; 
 char* r_str_word_get0 (char*,int) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static void update_asmfeatures_options(RCore *core, RConfigNode *node) {
	int i, argc;

	if (core && core->assembler && core->assembler->cur) {
		if (core->assembler->cur->features) {
			char *features = strdup (core->assembler->cur->features);
			argc = r_str_split (features, ',');
			for (i = 0; i < argc; i++) {
				node->options->free = free;
				const char *feature = r_str_word_get0 (features, i);
				if (feature) {
					r_list_append (node->options, strdup (feature));
				}
			}
			free (features);
		}
	}
}