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
struct channel {int type; int flags; int /*<<< orphan*/  fsm; struct channel* next; int /*<<< orphan*/  id; } ;
typedef  enum ctcm_channel_types { ____Placeholder_ctcm_channel_types } ctcm_channel_types ;

/* Variables and functions */
 int CHANNEL_FLAGS_INUSE ; 
 int CHANNEL_FLAGS_READ ; 
 int CHANNEL_FLAGS_RWMASK ; 
 int CHANNEL_FLAGS_WRITE ; 
 int /*<<< orphan*/  CTCM_DBF_TEXT_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  CTCM_FUNTAIL ; 
 int /*<<< orphan*/  CTCM_ID_SIZE ; 
 int CTCM_WRITE ; 
 int /*<<< orphan*/  CTC_DBF_ERROR ; 
 int /*<<< orphan*/  CTC_STATE_STOPPED ; 
 int /*<<< orphan*/  ERROR ; 
 struct channel* channels ; 
 int /*<<< orphan*/  fsm_newstate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct channel *channel_get(enum ctcm_channel_types type,
					char *id, int direction)
{
	struct channel *ch = channels;

	while (ch && (strncmp(ch->id, id, CTCM_ID_SIZE) || (ch->type != type)))
		ch = ch->next;
	if (!ch) {
		CTCM_DBF_TEXT_(ERROR, CTC_DBF_ERROR,
				"%s(%d, %s, %d) not found in channel list\n",
				CTCM_FUNTAIL, type, id, direction);
	} else {
		if (ch->flags & CHANNEL_FLAGS_INUSE)
			ch = NULL;
		else {
			ch->flags |= CHANNEL_FLAGS_INUSE;
			ch->flags &= ~CHANNEL_FLAGS_RWMASK;
			ch->flags |= (direction == CTCM_WRITE)
			    ? CHANNEL_FLAGS_WRITE : CHANNEL_FLAGS_READ;
			fsm_newstate(ch->fsm, CTC_STATE_STOPPED);
		}
	}
	return ch;
}