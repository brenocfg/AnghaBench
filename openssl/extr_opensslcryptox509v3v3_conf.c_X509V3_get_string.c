#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  db; TYPE_1__* db_meth; } ;
typedef  TYPE_2__ X509V3_CTX ;
struct TYPE_4__ {char* (* get_string ) (int /*<<< orphan*/ ,char const*,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  X509V3_F_X509V3_GET_STRING ; 
 int /*<<< orphan*/  X509V3_R_OPERATION_NOT_DEFINED ; 
 int /*<<< orphan*/  X509V3err (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* stub1 (int /*<<< orphan*/ ,char const*,char const*) ; 

char *X509V3_get_string(X509V3_CTX *ctx, const char *name, const char *section)
{
    if (!ctx->db || !ctx->db_meth || !ctx->db_meth->get_string) {
        X509V3err(X509V3_F_X509V3_GET_STRING, X509V3_R_OPERATION_NOT_DEFINED);
        return NULL;
    }
    if (ctx->db_meth->get_string)
        return ctx->db_meth->get_string(ctx->db, name, section);
    return NULL;
}