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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DT_UNICODE ; 
 int /*<<< orphan*/  MT_SEND_DATA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dword_to_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void api_send_unicode(uint32_t unicode) {
#ifdef API_ENABLE
    uint8_t chunk[4];
    dword_to_bytes(unicode, chunk);
    MT_SEND_DATA(DT_UNICODE, chunk, 5);
#endif
}