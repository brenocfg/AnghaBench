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
struct ucounts {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UCOUNT_USER_NAMESPACES ; 
 void dec_ucount (struct ucounts*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dec_user_namespaces(struct ucounts *ucounts)
{
	return dec_ucount(ucounts, UCOUNT_USER_NAMESPACES);
}