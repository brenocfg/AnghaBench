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
typedef  int /*<<< orphan*/  uint64_t ;
struct simple_pattern {int /*<<< orphan*/ * next; int /*<<< orphan*/ * child; int /*<<< orphan*/  match; int /*<<< orphan*/  mode; } ;
typedef  int /*<<< orphan*/  SIMPLE_PATTERN ;

/* Variables and functions */
 int /*<<< orphan*/  debug (int /*<<< orphan*/ ,char*,...) ; 

extern void simple_pattern_dump(uint64_t debug_type, SIMPLE_PATTERN *p)
{
    struct simple_pattern *root = (struct simple_pattern *)p;
    if(root==NULL) {
        debug(debug_type,"dump_pattern(NULL)");
        return;
    }
    debug(debug_type,"dump_pattern(%p) child=%p next=%p mode=%d match=%s", root, root->child, root->next, root->mode,
          root->match);
    if(root->child!=NULL)
        simple_pattern_dump(debug_type, (SIMPLE_PATTERN*)root->child);
    if(root->next!=NULL)
        simple_pattern_dump(debug_type, (SIMPLE_PATTERN*)root->next);
}