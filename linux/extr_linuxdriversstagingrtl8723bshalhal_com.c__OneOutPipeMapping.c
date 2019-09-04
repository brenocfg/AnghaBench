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
struct dvobj_priv {int /*<<< orphan*/ * RtOutPipe; int /*<<< orphan*/ * Queue2Pipe; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 struct dvobj_priv* adapter_to_dvobj (struct adapter*) ; 

__attribute__((used)) static void _OneOutPipeMapping(struct adapter *padapter)
{
	struct dvobj_priv *pdvobjpriv = adapter_to_dvobj(padapter);

	pdvobjpriv->Queue2Pipe[0] = pdvobjpriv->RtOutPipe[0];/* VO */
	pdvobjpriv->Queue2Pipe[1] = pdvobjpriv->RtOutPipe[0];/* VI */
	pdvobjpriv->Queue2Pipe[2] = pdvobjpriv->RtOutPipe[0];/* BE */
	pdvobjpriv->Queue2Pipe[3] = pdvobjpriv->RtOutPipe[0];/* BK */

	pdvobjpriv->Queue2Pipe[4] = pdvobjpriv->RtOutPipe[0];/* BCN */
	pdvobjpriv->Queue2Pipe[5] = pdvobjpriv->RtOutPipe[0];/* MGT */
	pdvobjpriv->Queue2Pipe[6] = pdvobjpriv->RtOutPipe[0];/* HIGH */
	pdvobjpriv->Queue2Pipe[7] = pdvobjpriv->RtOutPipe[0];/* TXCMD */
}