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
struct mcfqspi {int dummy; } ;

/* Variables and functions */
 int MCFQSPI_QDLYR_SPE ; 
 int mcfqspi_rd_qdlyr (struct mcfqspi*) ; 

__attribute__((used)) static bool mcfqspi_qdlyr_spe(struct mcfqspi *mcfqspi)
{
	return mcfqspi_rd_qdlyr(mcfqspi) & MCFQSPI_QDLYR_SPE;
}