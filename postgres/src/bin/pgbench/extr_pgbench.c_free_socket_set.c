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
typedef  int /*<<< orphan*/  socket_set ;

/* Variables and functions */
 int /*<<< orphan*/  pg_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_socket_set(socket_set *sa)
{
	pg_free(sa);
}