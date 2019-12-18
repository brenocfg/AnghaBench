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
struct iio_event_data {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  id; } ;
typedef  enum iio_modifier { ____Placeholder_iio_modifier } iio_modifier ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;
typedef  enum iio_chan_type { ____Placeholder_iio_chan_type } iio_chan_type ;

/* Variables and functions */
 int IIO_EVENT_CODE_EXTRACT_CHAN (int /*<<< orphan*/ ) ; 
 int IIO_EVENT_CODE_EXTRACT_CHAN2 (int /*<<< orphan*/ ) ; 
 int IIO_EVENT_CODE_EXTRACT_CHAN_TYPE (int /*<<< orphan*/ ) ; 
 int IIO_EVENT_CODE_EXTRACT_DIFF (int /*<<< orphan*/ ) ; 
 int IIO_EVENT_CODE_EXTRACT_DIR (int /*<<< orphan*/ ) ; 
 int IIO_EVENT_CODE_EXTRACT_MODIFIER (int /*<<< orphan*/ ) ; 
 int IIO_EVENT_CODE_EXTRACT_TYPE (int /*<<< orphan*/ ) ; 
 int IIO_EV_DIR_NONE ; 
 int IIO_NO_MOD ; 
 int /*<<< orphan*/  event_is_known (struct iio_event_data*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * iio_chan_type_name_spec ; 
 char** iio_ev_dir_text ; 
 char** iio_ev_type_text ; 
 char** iio_modifier_names ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void print_event(struct iio_event_data *event)
{
	enum iio_chan_type type = IIO_EVENT_CODE_EXTRACT_CHAN_TYPE(event->id);
	enum iio_modifier mod = IIO_EVENT_CODE_EXTRACT_MODIFIER(event->id);
	enum iio_event_type ev_type = IIO_EVENT_CODE_EXTRACT_TYPE(event->id);
	enum iio_event_direction dir = IIO_EVENT_CODE_EXTRACT_DIR(event->id);
	int chan = IIO_EVENT_CODE_EXTRACT_CHAN(event->id);
	int chan2 = IIO_EVENT_CODE_EXTRACT_CHAN2(event->id);
	bool diff = IIO_EVENT_CODE_EXTRACT_DIFF(event->id);

	if (!event_is_known(event)) {
		fprintf(stderr, "Unknown event: time: %lld, id: %llx\n",
			event->timestamp, event->id);

		return;
	}

	printf("Event: time: %lld, type: %s", event->timestamp,
	       iio_chan_type_name_spec[type]);

	if (mod != IIO_NO_MOD)
		printf("(%s)", iio_modifier_names[mod]);

	if (chan >= 0) {
		printf(", channel: %d", chan);
		if (diff && chan2 >= 0)
			printf("-%d", chan2);
	}

	printf(", evtype: %s", iio_ev_type_text[ev_type]);

	if (dir != IIO_EV_DIR_NONE)
		printf(", direction: %s", iio_ev_dir_text[dir]);

	printf("\n");
}