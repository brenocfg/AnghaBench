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
struct _meta_flags {int locked; int vivify; int la; int no_update; int no_reply; int set_stale; } ;

/* Variables and functions */

__attribute__((used)) static int _meta_flag_preparse(char *opts, size_t olen, struct _meta_flags *of) {
    unsigned int i;
    // NOTE: 'seen' is one of those need-to-microbench situation to do this via bit vector or
    // simple 8 bit array; need two divs and a shift vs a bit more memory.
    // Leave it simple for now, optimize later.
    uint8_t seen[127] = {0};
    // also count how many tokens should be necessary to parse.
    int tokens = 0;
    for (i = 0; i < olen; i++) {
        uint8_t o = (uint8_t)opts[i];
        // zero out repeat flags so we don't over-parse for return data.
        if (o >= 127 || seen[o] != 0) {
            return -1;
        }
        seen[o] = 1;
        // FIXME: alphabetize.
        switch (opts[i]) {
            case 'N':
                of->locked = 1;
                of->vivify = 1;
                tokens++;
                break;
            case 'T':
                tokens++;
                of->locked = 1;
                break;
            case 'R':
                of->locked = 1;
                tokens++;
                break;
            case 'l':
                of->la = 1;
                of->locked = 1; // need locked to delay LRU bump
                break;
            case 'O':
                tokens++;
                break;
            case 'k': // known but no special handling
            case 's':
            case 't':
            case 'c':
            case 'v':
            case 'f':
                break;
            case 'h':
                of->locked = 1; // need locked to delay LRU bump
                break;
            case 'u':
                of->no_update = 1;
                break;
            case 'q':
                of->no_reply = 1;
                break;
            // mset-related.
            case 'F':
            case 'S':
            case 'C':
                tokens++;
                break;
            case 'I':
                of->set_stale = 1;
                break;
            default: // unknown flag, bail.
                return -1;
        }
    }

    return tokens;
}