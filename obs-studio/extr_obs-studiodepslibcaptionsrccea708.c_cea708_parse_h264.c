#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  libcaption_stauts_t ;
typedef  scalar_t__ itu_t_t35_provider_code_t ;
typedef  scalar_t__ itu_t_t35_country_code_t ;
struct TYPE_3__ {scalar_t__ country; scalar_t__ provider; int user_identifier; int user_data_type_code; int directv_user_data_length; int /*<<< orphan*/  user_data; } ;
typedef  TYPE_1__ cea708_t ;

/* Variables and functions */
 int /*<<< orphan*/  LIBCAPTION_ERROR ; 
 int /*<<< orphan*/  LIBCAPTION_OK ; 
 int /*<<< orphan*/  cea708_parse_user_data_type_strcture (int const*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ t35_provider_atsc ; 
 scalar_t__ t35_provider_direct_tv ; 

libcaption_stauts_t cea708_parse_h264(const uint8_t* data, size_t size, cea708_t* cea708)
{
    if (3 > size) {
        goto error;
    }

    // I think the first few bytes need to be handled in mpeg
    cea708->country = (itu_t_t35_country_code_t)(data[0]);
    cea708->provider = (itu_t_t35_provider_code_t)((data[1] << 8) | data[2]);
    cea708->user_identifier = 0;
    cea708->user_data_type_code = 0;
    data += 3, size -= 3;

    if (t35_provider_atsc == cea708->provider) {
        if (4 > size) {
            goto error;
        }

        cea708->user_identifier = ((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3]);
        data += 4, size -= 4;
    }

    // where country and provider are zero
    // Im not sure what this extra byte is. It sonly seesm to come up in onCaptionInfo
    // h264 spec seems to describe this
    if (0 == cea708->provider && 0 == cea708->country) {
        if (1 > size) {
            goto error;
        }

        data += 1, size -= 1;
    } else if (t35_provider_atsc == cea708->provider || t35_provider_direct_tv == cea708->provider) {
        if (1 > size) {
            goto error;
        }

        cea708->user_data_type_code = data[0];
        data += 1, size -= 1;
    }

    if (t35_provider_direct_tv == cea708->provider) {
        if (1 > size) {
            goto error;
        }

        cea708->directv_user_data_length = data[0];
        data += 1, size -= 1;
    }

    if (3 == cea708->user_data_type_code && 2 <= size) {
        cea708_parse_user_data_type_strcture(data, size, &cea708->user_data);
    } else if (4 == cea708->user_data_type_code) {
        // additional_CEA_608_data
    } else if (5 == cea708->user_data_type_code) {
        // luma_PAM_data
    } else {
        // ATSC_reserved_user_data
    }

    return LIBCAPTION_OK;
error:
    return LIBCAPTION_ERROR;
}