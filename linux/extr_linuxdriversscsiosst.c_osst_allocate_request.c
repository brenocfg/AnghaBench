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
struct osst_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct osst_request* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct osst_request *osst_allocate_request(void)
{
	return kzalloc(sizeof(struct osst_request), GFP_KERNEL);
}