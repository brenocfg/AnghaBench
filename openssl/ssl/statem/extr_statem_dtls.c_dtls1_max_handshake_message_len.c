#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t max_cert_list; } ;
typedef  TYPE_1__ SSL ;

/* Variables and functions */
 size_t DTLS1_HM_HEADER_LENGTH ; 
 size_t SSL3_RT_MAX_ENCRYPTED_LENGTH ; 

__attribute__((used)) static size_t dtls1_max_handshake_message_len(const SSL *s)
{
    size_t max_len = DTLS1_HM_HEADER_LENGTH + SSL3_RT_MAX_ENCRYPTED_LENGTH;
    if (max_len < s->max_cert_list)
        return s->max_cert_list;
    return max_len;
}