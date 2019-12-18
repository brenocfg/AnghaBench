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
typedef  int /*<<< orphan*/  BACKEND_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  BACKEND_TYPE_GRAPHITE ; 
 int /*<<< orphan*/  BACKEND_TYPE_JSON ; 
 int /*<<< orphan*/  BACKEND_TYPE_KINESIS ; 
 int /*<<< orphan*/  BACKEND_TYPE_MONGODB ; 
 int /*<<< orphan*/  BACKEND_TYPE_OPENTSDB_USING_HTTP ; 
 int /*<<< orphan*/  BACKEND_TYPE_OPENTSDB_USING_TELNET ; 
 int /*<<< orphan*/  BACKEND_TYPE_PROMETEUS ; 
 int /*<<< orphan*/  BACKEND_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

BACKEND_TYPE backend_select_type(const char *type) {
    if(!strcmp(type, "graphite") || !strcmp(type, "graphite:plaintext")) {
        return BACKEND_TYPE_GRAPHITE;
    }
    else if(!strcmp(type, "opentsdb") || !strcmp(type, "opentsdb:telnet")) {
        return BACKEND_TYPE_OPENTSDB_USING_TELNET;
    }
    else if(!strcmp(type, "opentsdb:http") || !strcmp(type, "opentsdb:https")) {
        return BACKEND_TYPE_OPENTSDB_USING_HTTP;
    }
    else if (!strcmp(type, "json") || !strcmp(type, "json:plaintext")) {
        return BACKEND_TYPE_JSON;
    }
    else if (!strcmp(type, "prometheus_remote_write")) {
        return  BACKEND_TYPE_PROMETEUS;
    }
    else if (!strcmp(type, "kinesis") || !strcmp(type, "kinesis:plaintext")) {
        return BACKEND_TYPE_KINESIS;
    }
    else if (!strcmp(type, "mongodb") || !strcmp(type, "mongodb:plaintext")) {
        return BACKEND_TYPE_MONGODB;
    }

    return BACKEND_TYPE_UNKNOWN;
}