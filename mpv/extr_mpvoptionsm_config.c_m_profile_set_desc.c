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
struct m_profile {int /*<<< orphan*/  desc; } ;
typedef  int /*<<< orphan*/  bstr ;

/* Variables and functions */
 int /*<<< orphan*/  bstrto0 (struct m_profile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

void m_profile_set_desc(struct m_profile *p, bstr desc)
{
    talloc_free(p->desc);
    p->desc = bstrto0(p, desc);
}