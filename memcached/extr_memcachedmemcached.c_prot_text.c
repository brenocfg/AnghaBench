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
typedef  enum protocol { ____Placeholder_protocol } protocol ;

/* Variables and functions */
#define  ascii_prot 130 
#define  binary_prot 129 
#define  negotiating_prot 128 

__attribute__((used)) static const char *prot_text(enum protocol prot) {
    char *rv = "unknown";
    switch(prot) {
        case ascii_prot:
            rv = "ascii";
            break;
        case binary_prot:
            rv = "binary";
            break;
        case negotiating_prot:
            rv = "auto-negotiate";
            break;
    }
    return rv;
}