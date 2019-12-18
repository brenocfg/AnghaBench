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
struct mpv_node {int dummy; } ;
typedef  int /*<<< orphan*/  m_option_t ;

/* Variables and functions */
 struct mpv_node VAL (void*) ; 
 int /*<<< orphan*/  dup_node (void*,struct mpv_node*) ; 

__attribute__((used)) static int node_get(const m_option_t *opt, void *ta_parent,
                    struct mpv_node *dst, void *src)
{
    *dst = VAL(src);
    dup_node(ta_parent, dst);
    return 1;
}