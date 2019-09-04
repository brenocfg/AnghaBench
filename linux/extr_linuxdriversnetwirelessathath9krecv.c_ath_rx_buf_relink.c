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
struct TYPE_2__ {struct ath_rxbuf* buf_hold; } ;
struct ath_softc {TYPE_1__ rx; } ;
struct ath_rxbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath_rx_buf_link (struct ath_softc*,struct ath_rxbuf*,int) ; 

__attribute__((used)) static void ath_rx_buf_relink(struct ath_softc *sc, struct ath_rxbuf *bf,
			      bool flush)
{
	if (sc->rx.buf_hold)
		ath_rx_buf_link(sc, sc->rx.buf_hold, flush);

	sc->rx.buf_hold = bf;
}