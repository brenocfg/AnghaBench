#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ceph_osd_backoff {int /*<<< orphan*/  end; int /*<<< orphan*/  begin; int /*<<< orphan*/  id; int /*<<< orphan*/  spgid; } ;
struct TYPE_4__ {void* iov_base; int iov_len; } ;
struct TYPE_3__ {int /*<<< orphan*/  front_len; int /*<<< orphan*/  version; } ;
struct ceph_msg {int front_alloc_len; TYPE_2__ front; TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int CEPH_ENCODING_START_BLK_LEN ; 
 int /*<<< orphan*/  CEPH_MSG_OSD_BACKOFF ; 
 int /*<<< orphan*/  CEPH_OSD_BACKOFF_OP_ACK_BLOCK ; 
 int CEPH_PGID_ENCODING_LEN ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  ceph_encode_32 (void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_encode_64 (void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_encode_8 (void**,int /*<<< orphan*/ ) ; 
 struct ceph_msg* ceph_msg_new (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  encode_hoid (void**,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_spgid (void**,int /*<<< orphan*/ *) ; 
 scalar_t__ hoid_encoding_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ceph_msg *create_backoff_message(
				const struct ceph_osd_backoff *backoff,
				u32 map_epoch)
{
	struct ceph_msg *msg;
	void *p, *end;
	int msg_size;

	msg_size = CEPH_ENCODING_START_BLK_LEN +
			CEPH_PGID_ENCODING_LEN + 1; /* spgid */
	msg_size += 4 + 1 + 8; /* map_epoch, op, id */
	msg_size += CEPH_ENCODING_START_BLK_LEN +
			hoid_encoding_size(backoff->begin);
	msg_size += CEPH_ENCODING_START_BLK_LEN +
			hoid_encoding_size(backoff->end);

	msg = ceph_msg_new(CEPH_MSG_OSD_BACKOFF, msg_size, GFP_NOIO, true);
	if (!msg)
		return NULL;

	p = msg->front.iov_base;
	end = p + msg->front_alloc_len;

	encode_spgid(&p, &backoff->spgid);
	ceph_encode_32(&p, map_epoch);
	ceph_encode_8(&p, CEPH_OSD_BACKOFF_OP_ACK_BLOCK);
	ceph_encode_64(&p, backoff->id);
	encode_hoid(&p, end, backoff->begin);
	encode_hoid(&p, end, backoff->end);
	BUG_ON(p != end);

	msg->front.iov_len = p - msg->front.iov_base;
	msg->hdr.version = cpu_to_le16(1); /* MOSDBackoff v1 */
	msg->hdr.front_len = cpu_to_le32(msg->front.iov_len);

	return msg;
}