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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 scalar_t__ DOWN_LINK ; 
 int /*<<< orphan*/  SD1 ; 
 int /*<<< orphan*/  SD2 ; 
 int /*<<< orphan*/  sdWrite (int /*<<< orphan*/ *,scalar_t__ const*,int /*<<< orphan*/ ) ; 

void send_data(uint8_t link, const uint8_t* data, uint16_t size) {
    if (link == DOWN_LINK) {
        sdWrite(&SD1, data, size);
    } else {
        sdWrite(&SD2, data, size);
    }
}