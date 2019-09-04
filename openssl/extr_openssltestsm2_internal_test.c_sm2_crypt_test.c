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
typedef  int /*<<< orphan*/  EC_GROUP ;

/* Variables and functions */
 int /*<<< orphan*/  EC_GROUP_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_sha256 () ; 
 int /*<<< orphan*/  EVP_sm3 () ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_EC_group (char*,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  test_sm2_crypt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,char*,char*) ; 

__attribute__((used)) static int sm2_crypt_test(void)
{
    int testresult = 0;
    EC_GROUP *test_group =
        create_EC_group
        ("8542D69E4C044F18E8B92435BF6FF7DE457283915C45517D722EDB8B08F1DFC3",
         "787968B4FA32C3FD2417842E73BBFEFF2F3C848B6831D7E0EC65228B3937E498",
         "63E4C6D3B23B0C849CF84241484BFE48F61D59A5B16BA06E6E12D1DA27C5249A",
         "421DEBD61B62EAB6746434EBC3CC315E32220B3BADD50BDC4C4E6C147FEDD43D",
         "0680512BCBB42C07D47349D2153B70C4E5D7FDFCBFA36EA1A85841B9E46E09A2",
         "8542D69E4C044F18E8B92435BF6FF7DD297720630485628D5AE74EE7C32E79B7",
         "1");

    if (!TEST_ptr(test_group))
        goto done;

    if (!test_sm2_crypt(
            test_group,
            EVP_sm3(),
            "1649AB77A00637BD5E2EFE283FBF353534AA7F7CB89463F208DDBC2920BB0DA0",
            "encryption standard",
            "004C62EEFD6ECFC2B95B92FD6C3D9575148AFA17425546D49018E5388D49DD7B4F"
            "0092e8ff62146873c258557548500ab2df2a365e0609ab67640a1f6d57d7b17820"
            "008349312695a3e1d2f46905f39a766487f2432e95d6be0cb009fe8c69fd8825a7",
            "307B0220245C26FB68B1DDDDB12C4B6BF9F2B6D5FE60A383B0D18D1C4144ABF1"
            "7F6252E7022076CB9264C2A7E88E52B19903FDC47378F605E36811F5C07423A2"
            "4B84400F01B804209C3D7360C30156FAB7C80A0276712DA9D8094A634B766D3A"
            "285E07480653426D0413650053A89B41C418B0C3AAD00D886C00286467"))
        goto done;

    /* Same test as above except using SHA-256 instead of SM3 */
    if (!test_sm2_crypt(
            test_group,
            EVP_sha256(),
            "1649AB77A00637BD5E2EFE283FBF353534AA7F7CB89463F208DDBC2920BB0DA0",
            "encryption standard",
            "004C62EEFD6ECFC2B95B92FD6C3D9575148AFA17425546D49018E5388D49DD7B4F"
            "003da18008784352192d70f22c26c243174a447ba272fec64163dd4742bae8bc98"
            "00df17605cf304e9dd1dfeb90c015e93b393a6f046792f790a6fa4228af67d9588",
            "307B0220245C26FB68B1DDDDB12C4B6BF9F2B6D5FE60A383B0D18D1C4144ABF17F"
            "6252E7022076CB9264C2A7E88E52B19903FDC47378F605E36811F5C07423A24B84"
            "400F01B80420BE89139D07853100EFA763F60CBE30099EA3DF7F8F364F9D10A5E9"
            "88E3C5AAFC0413229E6C9AEE2BB92CAD649FE2C035689785DA33"))
        goto done;

    testresult = 1;
 done:
    EC_GROUP_free(test_group);

    return testresult;
}