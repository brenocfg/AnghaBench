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
typedef  int /*<<< orphan*/  m_option_t ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_int64 (int /*<<< orphan*/  const*,int*,double,int) ; 

__attribute__((used)) static void add_int(const m_option_t *opt, void *val, double add, bool wrap)
{
    int64_t tmp = *(int *)val;
    add_int64(opt, &tmp, add, wrap);
    *(int *)val = tmp;
}