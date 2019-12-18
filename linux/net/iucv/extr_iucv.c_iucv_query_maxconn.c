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
typedef  union iucv_param {int dummy; } iucv_param ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int __iucv_query_maxconn (void*,unsigned long*) ; 
 unsigned long iucv_max_pathid ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kzalloc (int,int) ; 

__attribute__((used)) static int iucv_query_maxconn(void)
{
	unsigned long max_pathid;
	void *param;
	int ccode;

	param = kzalloc(sizeof(union iucv_param), GFP_KERNEL | GFP_DMA);
	if (!param)
		return -ENOMEM;
	ccode = __iucv_query_maxconn(param, &max_pathid);
	if (ccode == 0)
		iucv_max_pathid = max_pathid;
	kfree(param);
	return ccode ? -EPERM : 0;
}