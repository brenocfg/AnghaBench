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
struct BannerOutput {scalar_t__ next; } ;
struct BannerBase64 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  banout_append (struct BannerOutput*,int,char*,int) ; 
 int /*<<< orphan*/  banout_append_base64 (struct BannerOutput*,int,char*,int,struct BannerBase64*) ; 
 int /*<<< orphan*/  banout_finalize_base64 (struct BannerOutput*,int,struct BannerBase64*) ; 
 int /*<<< orphan*/  banout_init (struct BannerOutput*) ; 
 int /*<<< orphan*/  banout_init_base64 (struct BannerBase64*) ; 
 int /*<<< orphan*/  banout_release (struct BannerOutput*) ; 
 int /*<<< orphan*/  banout_string_equals (struct BannerOutput*,int,char*) ; 
 int banout_string_length (struct BannerOutput*,int) ; 

int
banout_selftest(void)
{
    /*
     * Basic test
     */
    {
        struct BannerOutput banout[1];
        unsigned i;
        
        banout_init(banout);
        
        for (i=0; i<10; i++) {
            banout_append(banout, 1, "xxxx", 4);
            banout_append(banout, 2, "yyyyy", 5);
        }
        
        if (banout->next == 0)
            return 1;
        if (banout_string_length(banout, 1) != 40)
            return 1;
        if (banout_string_length(banout, 2) != 50)
            return 1;
        
        banout_release(banout);
        if (banout->next != 0)
            return 1;
    }
    
    /*
     * Test BASE64 encoding. We are going to do strings of various lengths
     * in order to test the boundary condition of finalizing various strings
     * properly
     */
    {
        struct BannerOutput banout[1];
        struct BannerBase64 base64[1];
    
        banout_init(banout);

        banout_init_base64(base64);
        banout_append_base64(banout, 1, "x", 1, base64);
        banout_finalize_base64(banout, 1, base64);
        
        banout_init_base64(base64);
        banout_append_base64(banout, 2, "bc", 2, base64);
        banout_finalize_base64(banout, 2, base64);
        
        banout_init_base64(base64);
        banout_append_base64(banout, 3, "mno", 3, base64);
        banout_finalize_base64(banout, 3, base64);
        
        banout_init_base64(base64);
        banout_append_base64(banout, 4, "stuv", 4, base64);
        banout_finalize_base64(banout, 4, base64);
        
        banout_init_base64(base64);
        banout_append_base64(banout, 5, "fghij", 5, base64);
        banout_finalize_base64(banout, 5, base64);
        
        
        if (!banout_string_equals(banout, 1, "eA=="))
            return 1;
        if (!banout_string_equals(banout, 2, "YmM="))
            return 1;
        if (!banout_string_equals(banout, 3, "bW5v"))
            return 1;
        if (!banout_string_equals(banout, 4, "c3R1dg=="))
            return 1;
        if (!banout_string_equals(banout, 5, "ZmdoaWo="))
            return 1;

        banout_release(banout);
    }
    
    
    return 0;
}