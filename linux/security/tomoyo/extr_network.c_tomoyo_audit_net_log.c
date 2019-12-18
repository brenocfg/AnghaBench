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
typedef  size_t u8 ;
struct tomoyo_request_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * tomoyo_proto_keyword ; 
 int /*<<< orphan*/ * tomoyo_socket_keyword ; 
 int tomoyo_supervisor (struct tomoyo_request_info*,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int tomoyo_audit_net_log(struct tomoyo_request_info *r,
				const char *family, const u8 protocol,
				const u8 operation, const char *address)
{
	return tomoyo_supervisor(r, "network %s %s %s %s\n", family,
				 tomoyo_proto_keyword[protocol],
				 tomoyo_socket_keyword[operation], address);
}