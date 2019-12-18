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
typedef  int /*<<< orphan*/  PACKET ;

/* Variables and functions */
 int /*<<< orphan*/  PACKET_buf_init (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 
 unsigned char* PACKET_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_length_prefixed_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PACKET_get_net_2 (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  PACKET_get_net_4 (int /*<<< orphan*/ *,unsigned long*) ; 
 size_t PACKET_remaining (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int serverinfo_find_extension(const unsigned char *serverinfo,
                                     size_t serverinfo_length,
                                     unsigned int extension_type,
                                     const unsigned char **extension_data,
                                     size_t *extension_length)
{
    PACKET pkt, data;

    *extension_data = NULL;
    *extension_length = 0;
    if (serverinfo == NULL || serverinfo_length == 0)
        return -1;

    if (!PACKET_buf_init(&pkt, serverinfo, serverinfo_length))
        return -1;

    for (;;) {
        unsigned int type = 0;
        unsigned long context = 0;

        /* end of serverinfo */
        if (PACKET_remaining(&pkt) == 0)
            return 0;           /* Extension not found */

        if (!PACKET_get_net_4(&pkt, &context)
                || !PACKET_get_net_2(&pkt, &type)
                || !PACKET_get_length_prefixed_2(&pkt, &data))
            return -1;

        if (type == extension_type) {
            *extension_data = PACKET_data(&data);
            *extension_length = PACKET_remaining(&data);;
            return 1;           /* Success */
        }
    }
    /* Unreachable */
}