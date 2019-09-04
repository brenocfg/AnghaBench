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
typedef  int /*<<< orphan*/  xdrproc_t ;
struct timeval {int member_0; int member_1; } ;
typedef  enum clnt_stat { ____Placeholder_clnt_stat } clnt_stat ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int clnt_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct timeval) ; 
 scalar_t__ xdr_void ; 

__attribute__((used)) static enum clnt_stat send_null(CLIENT *client)
{
    struct timeval timeout = {10, 100};

    return clnt_call(client, 0,
                     (xdrproc_t)xdr_void, NULL,
                     (xdrproc_t)xdr_void, NULL, timeout);
}