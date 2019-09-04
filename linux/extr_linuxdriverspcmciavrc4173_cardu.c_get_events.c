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
typedef  int /*<<< orphan*/  vrc4173_socket_t ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int BAT_DEAD_ST_CHG ; 
 int BAT_WAR_CHG ; 
 int BV_DETECT_GOOD ; 
 int BV_DETECT_MASK ; 
 int BV_DETECT_WARN ; 
 int CARD_DETECT1 ; 
 int CARD_DETECT2 ; 
 int CARD_DT_CHG ; 
 int /*<<< orphan*/  CARD_SC ; 
 int CARD_TYPE_IO ; 
 int /*<<< orphan*/  IF_STATUS ; 
 int /*<<< orphan*/  INT_GEN_CNT ; 
 int RDY_CHG ; 
 int READY ; 
 int /*<<< orphan*/  SS_BATDEAD ; 
 int /*<<< orphan*/  SS_BATWARN ; 
 int /*<<< orphan*/  SS_DETECT ; 
 int /*<<< orphan*/  SS_READY ; 
 int /*<<< orphan*/  SS_STSCHG ; 
 int STSCHG ; 
 int exca_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint16_t get_events(vrc4173_socket_t *socket)
{
	uint16_t events = 0;
	uint8_t csc, status;

	status = exca_readb(socket, IF_STATUS);
	csc = exca_readb(socket, CARD_SC);
	if ((csc & CARD_DT_CHG) &&
	    ((status & (CARD_DETECT1|CARD_DETECT2)) == (CARD_DETECT1|CARD_DETECT2)))
		events |= SS_DETECT;

	if ((csc & RDY_CHG) && (status & READY))
		events |= SS_READY;

	if (exca_readb(socket, INT_GEN_CNT) & CARD_TYPE_IO) {
		if ((csc & BAT_DEAD_ST_CHG) && (status & STSCHG))
			events |= SS_STSCHG;
	} else {
		if (csc & (BAT_WAR_CHG|BAT_DEAD_ST_CHG)) {
			if ((status & BV_DETECT_MASK) != BV_DETECT_GOOD) {
				if (status == BV_DETECT_WARN) events |= SS_BATWARN;
				else events |= SS_BATDEAD;
			}
		}
	}

	return events;
}