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
struct gb_connection {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GB_OPERATION_TIMEOUT_DEFAULT ; 
 int gb_operation_unidirectional_timeout (struct gb_connection*,int,void*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int gb_operation_unidirectional(struct gb_connection *connection,
				int type, void *request, int request_size)
{
	return gb_operation_unidirectional_timeout(connection, type,
			request, request_size, GB_OPERATION_TIMEOUT_DEFAULT);
}