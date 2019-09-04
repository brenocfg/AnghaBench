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
struct input_dev {int /*<<< orphan*/  led; } ;
struct hidp_session {unsigned char leds; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hidp_session*,unsigned int,unsigned int,int) ; 
 unsigned int EV_LED ; 
 unsigned char HIDP_DATA_RTYPE_OUPUT ; 
 unsigned char HIDP_TRANS_DATA ; 
 int /*<<< orphan*/  LED_CAPSL ; 
 int /*<<< orphan*/  LED_COMPOSE ; 
 int /*<<< orphan*/  LED_KANA ; 
 int /*<<< orphan*/  LED_NUML ; 
 int /*<<< orphan*/  LED_SCROLLL ; 
 int hidp_send_intr_message (struct hidp_session*,unsigned char,unsigned char*,int) ; 
 struct hidp_session* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hidp_input_event(struct input_dev *dev, unsigned int type,
			    unsigned int code, int value)
{
	struct hidp_session *session = input_get_drvdata(dev);
	unsigned char newleds;
	unsigned char hdr, data[2];

	BT_DBG("session %p type %d code %d value %d",
	       session, type, code, value);

	if (type != EV_LED)
		return -1;

	newleds = (!!test_bit(LED_KANA,    dev->led) << 3) |
		  (!!test_bit(LED_COMPOSE, dev->led) << 3) |
		  (!!test_bit(LED_SCROLLL, dev->led) << 2) |
		  (!!test_bit(LED_CAPSL,   dev->led) << 1) |
		  (!!test_bit(LED_NUML,    dev->led) << 0);

	if (session->leds == newleds)
		return 0;

	session->leds = newleds;

	hdr = HIDP_TRANS_DATA | HIDP_DATA_RTYPE_OUPUT;
	data[0] = 0x01;
	data[1] = newleds;

	return hidp_send_intr_message(session, hdr, data, 2);
}