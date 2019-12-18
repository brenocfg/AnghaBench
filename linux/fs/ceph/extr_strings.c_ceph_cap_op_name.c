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
#define  CEPH_CAP_OP_DROP 140 
#define  CEPH_CAP_OP_EXPORT 139 
#define  CEPH_CAP_OP_FLUSH 138 
#define  CEPH_CAP_OP_FLUSHSNAP 137 
#define  CEPH_CAP_OP_FLUSHSNAP_ACK 136 
#define  CEPH_CAP_OP_FLUSH_ACK 135 
#define  CEPH_CAP_OP_GRANT 134 
#define  CEPH_CAP_OP_IMPORT 133 
#define  CEPH_CAP_OP_RELEASE 132 
#define  CEPH_CAP_OP_RENEW 131 
#define  CEPH_CAP_OP_REVOKE 130 
#define  CEPH_CAP_OP_TRUNC 129 
#define  CEPH_CAP_OP_UPDATE 128 

const char *ceph_cap_op_name(int op)
{
	switch (op) {
	case CEPH_CAP_OP_GRANT: return "grant";
	case CEPH_CAP_OP_REVOKE: return "revoke";
	case CEPH_CAP_OP_TRUNC: return "trunc";
	case CEPH_CAP_OP_EXPORT: return "export";
	case CEPH_CAP_OP_IMPORT: return "import";
	case CEPH_CAP_OP_UPDATE: return "update";
	case CEPH_CAP_OP_DROP: return "drop";
	case CEPH_CAP_OP_FLUSH: return "flush";
	case CEPH_CAP_OP_FLUSH_ACK: return "flush_ack";
	case CEPH_CAP_OP_FLUSHSNAP: return "flushsnap";
	case CEPH_CAP_OP_FLUSHSNAP_ACK: return "flushsnap_ack";
	case CEPH_CAP_OP_RELEASE: return "release";
	case CEPH_CAP_OP_RENEW: return "renew";
	}
	return "???";
}