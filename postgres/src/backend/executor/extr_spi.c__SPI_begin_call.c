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
struct TYPE_2__ {int /*<<< orphan*/  execSubid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentSubTransactionId () ; 
 int SPI_ERROR_UNCONNECTED ; 
 TYPE_1__* _SPI_current ; 
 int /*<<< orphan*/  _SPI_execmem () ; 

__attribute__((used)) static int
_SPI_begin_call(bool use_exec)
{
	if (_SPI_current == NULL)
		return SPI_ERROR_UNCONNECTED;

	if (use_exec)
	{
		/* remember when the Executor operation started */
		_SPI_current->execSubid = GetCurrentSubTransactionId();
		/* switch to the Executor memory context */
		_SPI_execmem();
	}

	return 0;
}