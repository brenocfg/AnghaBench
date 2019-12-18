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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ sa_family_t ;

/* Variables and functions */
 scalar_t__ const AF_INET ; 

uint16_t
ip_checksum(const sa_family_t af, const uint8_t *payload, const int len_payload,
            const uint8_t *src_addr, const uint8_t *dest_addr, const int proto)
{
    uint32_t sum = 0;
    int addr_len = (af == AF_INET) ? 4 : 16;

    /*
     * make 16 bit words out of every two adjacent 8 bit words and  */
    /* calculate the sum of all 16 bit words
     */
    for (int i = 0; i < len_payload; i += 2)
    {
        sum +=  (uint16_t)(((payload[i] << 8) & 0xFF00)
                           +((i + 1 < len_payload) ? (payload[i + 1] & 0xFF) : 0));

    }

    /*
     * add the pseudo header which contains the IP source and destination
     * addresses
     */
    for (int i = 0; i < addr_len; i += 2)
    {
        sum += (uint16_t)((src_addr[i] << 8) & 0xFF00) + (src_addr[i + 1] & 0xFF);

    }
    for (int i = 0; i < addr_len; i += 2)
    {
        sum += (uint16_t)((dest_addr[i] << 8) & 0xFF00) + (dest_addr[i + 1] & 0xFF);
    }

    /* the length of the payload */
    sum += (uint16_t)len_payload;

    /* The next header or proto field*/
    sum += (uint16_t)proto;

    /*
     * keep only the last 16 bits of the 32 bit calculated sum and add
     * the carries
     */
    while (sum >> 16)
    {
        sum = (sum & 0xFFFF) + (sum >> 16);
    }

    /* Take the one's complement of sum */
    return ((uint16_t) ~sum);
}