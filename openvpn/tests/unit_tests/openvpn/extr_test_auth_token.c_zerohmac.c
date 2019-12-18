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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int AUTH_TOKEN_SESSION_ID_LEN ; 
 char* SESSION_ID_PREFIX ; 
 int /*<<< orphan*/  memset (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void
zerohmac(char *token)
{
    char *hmacstart = token + AUTH_TOKEN_SESSION_ID_LEN
                      + strlen(SESSION_ID_PREFIX) + 2*sizeof(uint64_t);
    memset(hmacstart, 0x8d, strlen(hmacstart));
}