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

/* Variables and functions */
#define  DTLS1_2_VERSION 134 
#define  DTLS1_VERSION 133 
 size_t OSSL_NELEM (struct protocol_versions const*) ; 
#define  SSL3_VERSION 132 
#define  TLS1_1_VERSION 131 
#define  TLS1_2_VERSION 130 
#define  TLS1_3_VERSION 129 
#define  TLS1_VERSION 128 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static int protocol_from_string(const char *value)
{
    struct protocol_versions {
        const char *name;
        int version;
    };
    static const struct protocol_versions versions[] = {
        {"ssl3", SSL3_VERSION},
        {"tls1", TLS1_VERSION},
        {"tls1.1", TLS1_1_VERSION},
        {"tls1.2", TLS1_2_VERSION},
        {"tls1.3", TLS1_3_VERSION},
        {"dtls1", DTLS1_VERSION},
        {"dtls1.2", DTLS1_2_VERSION}};
    size_t i;
    size_t n = OSSL_NELEM(versions);

    for (i = 0; i < n; i++)
        if (strcmp(versions[i].name, value) == 0)
            return versions[i].version;
    return -1;
}