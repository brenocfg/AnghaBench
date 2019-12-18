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
struct connection_ops {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct connection_ops const*) ; 
 struct connection_ops const* conn_protseq_list ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static const struct connection_ops *rpcrt4_get_conn_protseq_ops(const char *protseq)
{
    unsigned int i;
    for(i = 0; i < ARRAY_SIZE(conn_protseq_list); i++)
        if (!strcmp(conn_protseq_list[i].name, protseq))
            return &conn_protseq_list[i];
    return NULL;
}