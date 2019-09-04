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
struct BannerOutput {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ntp_priv (unsigned char const*,unsigned int,struct BannerOutput*,unsigned int*) ; 

__attribute__((used)) static void
ntp_v2_parse(const unsigned char *px,
           unsigned length,
           struct BannerOutput *banout,
           unsigned *request_id)
{
    unsigned mode;
    
    if (length < 4)
        return;
    
    /* Validate: response bit is set */
    if ((px[0]>>7) != 1)
        return;
        
    /* Validate: this is version 2 */
    if (((px[0]>>3)&7) != 2)
        return;
    
    /* Extract: mode */
    mode = px[0] & 7;
    switch (mode) {
        case 6: /* control */
            break;
        case 7:
            ntp_priv(px, length, banout, request_id);
            break;
    }
    
    
    
}