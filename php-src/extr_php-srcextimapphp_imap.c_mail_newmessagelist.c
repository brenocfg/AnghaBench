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
typedef  int /*<<< orphan*/  MESSAGELIST ;

/* Variables and functions */
 int /*<<< orphan*/  fs_get (int) ; 
 scalar_t__ memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

MESSAGELIST *mail_newmessagelist(void)
{
	return (MESSAGELIST *) memset(fs_get(sizeof(MESSAGELIST)), 0, sizeof(MESSAGELIST));
}