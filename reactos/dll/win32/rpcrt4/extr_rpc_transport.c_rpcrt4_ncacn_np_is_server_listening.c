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
typedef  int /*<<< orphan*/  RPC_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  I_RpcFree (char*) ; 
 int /*<<< orphan*/  is_pipe_listening (char*) ; 
 char* ncacn_pipe_name (char const*,...) ; 

__attribute__((used)) static RPC_STATUS rpcrt4_ncacn_np_is_server_listening(const char *endpoint)
{
  char *pipe_name;
  RPC_STATUS status;

#ifdef __REACTOS__
  pipe_name = ncacn_pipe_name(NULL, endpoint);
#else
  pipe_name = ncacn_pipe_name(endpoint);
#endif
  status = is_pipe_listening(pipe_name);
  I_RpcFree(pipe_name);
  return status;
}