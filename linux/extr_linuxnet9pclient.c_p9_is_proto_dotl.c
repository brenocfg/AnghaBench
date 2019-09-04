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
struct p9_client {scalar_t__ proto_version; } ;

/* Variables and functions */
 scalar_t__ p9_proto_2000L ; 

inline int p9_is_proto_dotl(struct p9_client *clnt)
{
	return clnt->proto_version == p9_proto_2000L;
}