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
struct dlm_lock_resource {int dummy; } ;
struct dlm_lock {int dummy; } ;
struct dlm_ctxt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_AST ; 
 int dlm_send_proxy_ast_msg (struct dlm_ctxt*,struct dlm_lock_resource*,struct dlm_lock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int dlm_send_proxy_ast(struct dlm_ctxt *dlm,
				     struct dlm_lock_resource *res,
				     struct dlm_lock *lock,
				     int flags)
{
	return dlm_send_proxy_ast_msg(dlm, res, lock, DLM_AST,
				      0, flags);
}