#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* Value; struct TYPE_4__* Keyword; } ;
typedef  TYPE_1__* PKULL_M_CRED_ATTRIBUTE ;

/* Variables and functions */
 int /*<<< orphan*/  LocalFree (TYPE_1__*) ; 

void kull_m_cred_attribute_delete(PKULL_M_CRED_ATTRIBUTE Attribute)
{
	if(Attribute)
	{
		if(Attribute->Keyword)
			LocalFree(Attribute->Keyword);
		if(Attribute->Value)
			LocalFree(Attribute->Value);
		LocalFree(Attribute);
	}
}