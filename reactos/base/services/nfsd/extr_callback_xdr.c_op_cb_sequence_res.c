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
struct cb_sequence_res {int /*<<< orphan*/  ok; int /*<<< orphan*/  status; } ;
typedef  int /*<<< orphan*/  bool_t ;
typedef  int /*<<< orphan*/  XDR ;

/* Variables and functions */
 int /*<<< orphan*/  CBX_ERR (char*) ; 
 int /*<<< orphan*/  cb_sequence_res_discrim ; 
 int /*<<< orphan*/  xdr_union (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xdr_void ; 

__attribute__((used)) static bool_t op_cb_sequence_res(XDR *xdr, struct cb_sequence_res *res)
{
    bool_t result;

    result = xdr_union(xdr, &res->status, (char*)&res->ok,
        cb_sequence_res_discrim, (xdrproc_t)xdr_void);
    if (!result) { CBX_ERR("seq:argop.args"); goto out; }
out:
    return result;
}