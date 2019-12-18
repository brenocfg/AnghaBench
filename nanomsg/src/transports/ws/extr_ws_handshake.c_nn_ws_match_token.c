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
 int NN_WS_HANDSHAKE_MATCH ; 
 int NN_WS_HANDSHAKE_NOMATCH ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 scalar_t__ tolower (char const) ; 

__attribute__((used)) static int nn_ws_match_token (const char* token, const char **subj,
    int case_insensitive, int ignore_leading_sp)
{
    const char *pos;

    nn_assert (token && *subj);

    pos = *subj;

    if (ignore_leading_sp) {
        while (*pos == '\x20' && *pos) {
            pos++;
        }
    }

    if (case_insensitive) {
        while (*token && *pos) {
            if (tolower (*token) != tolower (*pos))
                return NN_WS_HANDSHAKE_NOMATCH;
            token++;
            pos++;
        }
    }
    else {
        while (*token && *pos) {
            if (*token != *pos)
                return NN_WS_HANDSHAKE_NOMATCH;
            token++;
            pos++;
        }
    }

    /*  Encountered end of subject before matching completed. */
    if (!*pos && *token)
        return NN_WS_HANDSHAKE_NOMATCH;

    /*  Entire token has been matched. */
    nn_assert (!*token);

    /*  On success, advance subject position. */
    *subj = pos;

    return NN_WS_HANDSHAKE_MATCH;
}