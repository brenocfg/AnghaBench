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
typedef  int /*<<< orphan*/  u16 ;
struct mcfqspi {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ MCFQSPI_QDLYR ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mcfqspi_wr_qdlyr(struct mcfqspi *mcfqspi, u16 val)
{
	writew(val, mcfqspi->iobase + MCFQSPI_QDLYR);
}