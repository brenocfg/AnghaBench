#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct priv {int /*<<< orphan*/  dvdnav; int /*<<< orphan*/ * filename; int /*<<< orphan*/  dvd_speed; TYPE_1__* opts; } ;
struct TYPE_7__ {struct priv* priv; } ;
typedef  TYPE_2__ stream_t ;
struct TYPE_6__ {int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 scalar_t__ DVDNAV_STATUS_OK ; 
 int /*<<< orphan*/  MP_ERR (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dvd_set_speed (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvdnav_get_title_string (int /*<<< orphan*/ ,char const**) ; 
 scalar_t__ dvdnav_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ dvdnav_set_PGC_positioning_flag (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dvdnav_set_readahead_flag (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strdup (char*) ; 

__attribute__((used)) static struct priv *new_dvdnav_stream(stream_t *stream, char *filename)
{
    struct priv *priv = stream->priv;
    const char *title_str;

    if (!filename)
        return NULL;

    if (!(priv->filename = strdup(filename)))
        return NULL;

    priv->dvd_speed = priv->opts->speed;
    dvd_set_speed(stream, priv->filename, priv->dvd_speed);

    if (dvdnav_open(&(priv->dvdnav), priv->filename) != DVDNAV_STATUS_OK) {
        free(priv->filename);
        priv->filename = NULL;
        return NULL;
    }

    if (!priv->dvdnav)
        return NULL;

    dvdnav_set_readahead_flag(priv->dvdnav, 1);
    if (dvdnav_set_PGC_positioning_flag(priv->dvdnav, 1) != DVDNAV_STATUS_OK)
        MP_ERR(stream, "stream_dvdnav, failed to set PGC positioning\n");
    /* report the title?! */
    dvdnav_get_title_string(priv->dvdnav, &title_str);

    return priv;
}