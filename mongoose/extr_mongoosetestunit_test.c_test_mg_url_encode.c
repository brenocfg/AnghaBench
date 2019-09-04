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
struct mg_str {scalar_t__ p; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_MG_STREQ (struct mg_str,char*) ; 
 struct mg_str MG_MK_STR (char*) ; 
 int MG_URL_ENCODE_F_SPACE_AS_PLUS ; 
 int MG_URL_ENCODE_F_UPPERCASE_HEX ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  mg_mk_str (char*) ; 
 struct mg_str mg_url_encode (struct mg_str const) ; 
 struct mg_str mg_url_encode_opt (struct mg_str const,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static const char *test_mg_url_encode(void) {
  const struct mg_str encode_me =
      MG_MK_STR("I'm a.little_tea-pot,here's$my;spout~oink(oink)oink/!");
  {
    struct mg_str encoded = mg_url_encode(encode_me);
    ASSERT_MG_STREQ(
        encoded,
        "I%27m%20a.little_tea-pot,here%27s$my;spout~oink(oink)oink/%21");
    free((void *) encoded.p);
  }
  {
    struct mg_str encoded = mg_url_encode_opt(encode_me, mg_mk_str(NULL), 0);
    ASSERT_MG_STREQ(encoded,
                    "I%27m%20a%2elittle%5ftea%2dpot%2chere%27s%24my%3bspout%"
                    "7eoink%28oink%29oink%2f%21");
    free((void *) encoded.p);
  }
  {
    struct mg_str encoded = mg_url_encode_opt(encode_me, mg_mk_str(" /!"),
                                              MG_URL_ENCODE_F_UPPERCASE_HEX);
    ASSERT_MG_STREQ(encoded,
                    "I%27m "
                    "a%2Elittle%5Ftea%2Dpot%2Chere%27s%24my%3Bspout%7Eoink%"
                    "28oink%29oink/!");
    free((void *) encoded.p);
  }
  {
    struct mg_str encoded = mg_url_encode_opt(
        encode_me, mg_mk_str("/!"),
        MG_URL_ENCODE_F_SPACE_AS_PLUS | MG_URL_ENCODE_F_UPPERCASE_HEX);
    ASSERT_MG_STREQ(encoded,
                    "I%27m+a%2Elittle%5Ftea%2Dpot%2Chere%27s%24my%3Bspout%"
                    "7Eoink%28oink%29oink/!");
    free((void *) encoded.p);
  }
  return NULL;
}