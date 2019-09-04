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
struct ceph_msg_footer_old {int dummy; } ;
struct ceph_msg_footer {int dummy; } ;
struct ceph_connection {int peer_features; } ;

/* Variables and functions */
 int CEPH_FEATURE_MSG_AUTH ; 

__attribute__((used)) static size_t sizeof_footer(struct ceph_connection *con)
{
	return (con->peer_features & CEPH_FEATURE_MSG_AUTH) ?
	    sizeof(struct ceph_msg_footer) :
	    sizeof(struct ceph_msg_footer_old);
}