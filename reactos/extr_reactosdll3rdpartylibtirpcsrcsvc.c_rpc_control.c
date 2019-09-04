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
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
#define  RPC_SVC_CONNMAXREC_GET 129 
#define  RPC_SVC_CONNMAXREC_SET 128 
 int /*<<< orphan*/  TRUE ; 
 int __svc_maxrec ; 

bool_t
rpc_control (int what, void *arg)
{
  int val;

  switch (what)
    {
    case RPC_SVC_CONNMAXREC_SET:
      val = *(int *) arg;
      if (val <= 0)
	return FALSE;
      __svc_maxrec = val;
      return TRUE;
    case RPC_SVC_CONNMAXREC_GET:
      *(int *) arg = __svc_maxrec;
      return TRUE;
    default:
      break;
    }
  return FALSE;
}