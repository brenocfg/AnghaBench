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
typedef  int /*<<< orphan*/  uuid_le ;
struct mei_client {unsigned char max_msg_length; unsigned char protocol_version; } ;
struct mei_connect_client_data {struct mei_client out_client_properties; int /*<<< orphan*/  const in_client_uuid; } ;
struct mei {int verbose; int fd; int initialized; unsigned char buf_size; unsigned char prot_ver; int /*<<< orphan*/  const guid; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  IOCTL_MEI_CONNECT_CLIENT ; 
 int /*<<< orphan*/  O_RDWR ; 
 int ioctl (int,int /*<<< orphan*/ ,struct mei_connect_client_data*) ; 
 int /*<<< orphan*/  mei_deinit (struct mei*) ; 
 int /*<<< orphan*/  mei_err (struct mei*,char*,...) ; 
 int /*<<< orphan*/  mei_msg (struct mei*,char*,unsigned char) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  memset (struct mei_connect_client_data*,int /*<<< orphan*/ ,int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool mei_init(struct mei *me, const uuid_le *guid,
		unsigned char req_protocol_version, bool verbose)
{
	int result;
	struct mei_client *cl;
	struct mei_connect_client_data data;

	me->verbose = verbose;

	me->fd = open("/dev/mei0", O_RDWR);
	if (me->fd == -1) {
		mei_err(me, "Cannot establish a handle to the Intel MEI driver\n");
		goto err;
	}
	memcpy(&me->guid, guid, sizeof(*guid));
	memset(&data, 0, sizeof(data));
	me->initialized = true;

	memcpy(&data.in_client_uuid, &me->guid, sizeof(me->guid));
	result = ioctl(me->fd, IOCTL_MEI_CONNECT_CLIENT, &data);
	if (result) {
		mei_err(me, "IOCTL_MEI_CONNECT_CLIENT receive message. err=%d\n", result);
		goto err;
	}
	cl = &data.out_client_properties;
	mei_msg(me, "max_message_length %d\n", cl->max_msg_length);
	mei_msg(me, "protocol_version %d\n", cl->protocol_version);

	if ((req_protocol_version > 0) &&
	     (cl->protocol_version != req_protocol_version)) {
		mei_err(me, "Intel MEI protocol version not supported\n");
		goto err;
	}

	me->buf_size = cl->max_msg_length;
	me->prot_ver = cl->protocol_version;

	return true;
err:
	mei_deinit(me);
	return false;
}