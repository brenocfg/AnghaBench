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
struct mixart_pipe {int status; int /*<<< orphan*/  group_uid; } ;
struct mixart_msg {int size; struct mixart_clock_properties* data; int /*<<< orphan*/  uid; int /*<<< orphan*/  message_id; } ;
struct mixart_mgr {TYPE_1__* pci; int /*<<< orphan*/  uid_console_manager; } ;
struct mixart_clock_properties_resp {scalar_t__ status; scalar_t__ clock_mode; } ;
struct mixart_clock_properties {unsigned int frequency; int nb_callers; int /*<<< orphan*/ * uid_caller; scalar_t__ clock_mode; int /*<<< orphan*/  clock_generic_type; } ;
typedef  int /*<<< orphan*/  clock_properties ;
typedef  int /*<<< orphan*/  clock_prop_resp ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGT_INTERNAL_CLOCK ; 
 int /*<<< orphan*/  CGT_NO_CLOCK ; 
 scalar_t__ CM_STANDALONE ; 
 int EINVAL ; 
 int /*<<< orphan*/  MSG_CLOCK_SET_PROPERTIES ; 
#define  PIPE_CLOCK_SET 129 
#define  PIPE_RUNNING 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  memset (struct mixart_clock_properties*,int /*<<< orphan*/ ,int) ; 
 int snd_mixart_send_msg (struct mixart_mgr*,struct mixart_msg*,int,struct mixart_clock_properties_resp*) ; 

__attribute__((used)) static int mixart_set_clock(struct mixart_mgr *mgr,
			    struct mixart_pipe *pipe, unsigned int rate)
{
	struct mixart_msg request;
	struct mixart_clock_properties clock_properties;
	struct mixart_clock_properties_resp clock_prop_resp;
	int err;

	switch(pipe->status) {
	case PIPE_CLOCK_SET:
		break;
	case PIPE_RUNNING:
		if(rate != 0)
			break;
		/* fall through */
	default:
		if(rate == 0)
			return 0; /* nothing to do */
		else {
			dev_err(&mgr->pci->dev,
				"error mixart_set_clock(%d) called with wrong pipe->status !\n",
				rate);
			return -EINVAL;
		}
	}

	memset(&clock_properties, 0, sizeof(clock_properties));
	clock_properties.clock_generic_type = (rate != 0) ? CGT_INTERNAL_CLOCK : CGT_NO_CLOCK;
	clock_properties.clock_mode = CM_STANDALONE;
	clock_properties.frequency = rate;
	clock_properties.nb_callers = 1; /* only one entry in uid_caller ! */
	clock_properties.uid_caller[0] = pipe->group_uid;

	dev_dbg(&mgr->pci->dev, "mixart_set_clock to %d kHz\n", rate);

	request.message_id = MSG_CLOCK_SET_PROPERTIES;
	request.uid = mgr->uid_console_manager;
	request.data = &clock_properties;
	request.size = sizeof(clock_properties);

	err = snd_mixart_send_msg(mgr, &request, sizeof(clock_prop_resp), &clock_prop_resp);
	if (err < 0 || clock_prop_resp.status != 0 || clock_prop_resp.clock_mode != CM_STANDALONE) {
		dev_err(&mgr->pci->dev,
			"error MSG_CLOCK_SET_PROPERTIES err=%x stat=%x mod=%x !\n",
			err, clock_prop_resp.status, clock_prop_resp.clock_mode);
		return -EINVAL;
	}

	if(rate)  pipe->status = PIPE_CLOCK_SET;
	else      pipe->status = PIPE_RUNNING;

	return 0;
}