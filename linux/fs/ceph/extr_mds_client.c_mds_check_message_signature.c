#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ceph_msg {TYPE_1__* con; } ;
struct ceph_auth_handshake {int dummy; } ;
struct ceph_mds_session {struct ceph_auth_handshake s_auth; } ;
struct TYPE_2__ {struct ceph_mds_session* private; } ;

/* Variables and functions */
 int ceph_auth_check_message_signature (struct ceph_auth_handshake*,struct ceph_msg*) ; 

__attribute__((used)) static int mds_check_message_signature(struct ceph_msg *msg)
{
       struct ceph_mds_session *s = msg->con->private;
       struct ceph_auth_handshake *auth = &s->s_auth;

       return ceph_auth_check_message_signature(auth, msg);
}