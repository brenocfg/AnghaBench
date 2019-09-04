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
typedef  int /*<<< orphan*/  u8 ;
struct gb_operation {int dummy; } ;
struct gb_connection {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 struct gb_operation* gb_operation_create_flags (struct gb_connection*,int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct gb_operation *
gb_operation_create(struct gb_connection *connection,
				u8 type, size_t request_size,
				size_t response_size, gfp_t gfp)
{
	return gb_operation_create_flags(connection, type, request_size,
						response_size, 0, gfp);
}