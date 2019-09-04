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

/* Variables and functions */
 int ENOENT ; 
 int ENOTCONN ; 

__attribute__((used)) static int normalize_watch_error(int err)
{
	/*
	 * Translate ENOENT -> ENOTCONN so that a delete->disconnection
	 * notification and a failure to reconnect because we raced with
	 * the delete appear the same to the user.
	 */
	if (err == -ENOENT)
		err = -ENOTCONN;

	return err;
}