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
 double VAL (void*) ; 
 int double_get (int /*<<< orphan*/  const*,void*,struct mpv_node*,double*) ; 

__attribute__((used)) static int float_get(const m_option_t *opt, void *ta_parent,
                     struct mpv_node *dst, void *src)
{
    double tmp = VAL(src);
    return double_get(opt, ta_parent, dst, &tmp);
}