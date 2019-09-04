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
typedef  int uint64_t ;
struct BlackRock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blackrock_init (struct BlackRock*,int,int /*<<< orphan*/ ,int) ; 
 int blackrock_shuffle (struct BlackRock*,int) ; 
 int blackrock_unshuffle (struct BlackRock*,int) ; 
 int blackrock_verify (struct BlackRock*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 

int
blackrock_selftest(void)
{
    uint64_t i;
    uint64_t range;

    /* @marshray
     * Basic test of decryption. I take the index, encrypt it, then decrypt it,
     * which means I should get the original index back again. Only, it's not
     * working. The decryption fails. The reason it's failing is obvious -- I'm
     * just not seeing it though. The error is probably in the 'UNENCRYPT()'
     * function above.
     */
    {
        struct BlackRock br;
        
        blackrock_init(&br, 1000, 0, 4);

        for (i=0; i<10; i++) {
            uint64_t result, result2;
            result = blackrock_shuffle(&br, i);
            result2 = blackrock_unshuffle(&br, result);
            if (i != result2)
                return 1; /*fail*/
        }

    }


    range = 3015 * 3;

    for (i=0; i<5; i++) {
        struct BlackRock br;
        int is_success;

        range += 10 + i;
        range *= 2;

        blackrock_init(&br, range, time(0), 4);

        is_success = blackrock_verify(&br, range);
        if (!is_success) {
            fprintf(stderr, "BLACKROCK: randomization failed\n");
            return 1; /*fail*/
        }
    }

    return 0; /*success*/
}