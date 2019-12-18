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
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 size_t CUSE_CONNTBL_LEN ; 
 size_t MAJOR (int /*<<< orphan*/ ) ; 
 size_t MINOR (int /*<<< orphan*/ ) ; 
 struct list_head* cuse_conntbl ; 

__attribute__((used)) static struct list_head *cuse_conntbl_head(dev_t devt)
{
	return &cuse_conntbl[(MAJOR(devt) + MINOR(devt)) % CUSE_CONNTBL_LEN];
}