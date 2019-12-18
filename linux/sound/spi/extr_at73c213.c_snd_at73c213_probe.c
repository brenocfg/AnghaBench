#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct at73c213_board_info* platform_data; } ;
struct spi_device {TYPE_1__ dev; } ;
struct snd_card {char* driver; char* shortname; int /*<<< orphan*/  longname; struct snd_at73c213* private_data; } ;
struct snd_at73c213 {int irq; int /*<<< orphan*/  ssc; struct at73c213_board_info* board; struct spi_device* spi; } ;
struct at73c213_board_info {int ssc_id; char* shortname; int /*<<< orphan*/  dac_clk; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct snd_card*) ; 
 int snd_at73c213_dev_init (struct snd_card*,struct spi_device*) ; 
 int /*<<< orphan*/  snd_card_free (struct snd_card*) ; 
 int snd_card_new (TYPE_1__*,int,char*,int /*<<< orphan*/ ,int,struct snd_card**) ; 
 int snd_card_register (struct snd_card*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  ssc_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssc_request (int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int snd_at73c213_probe(struct spi_device *spi)
{
	struct snd_card			*card;
	struct snd_at73c213		*chip;
	struct at73c213_board_info	*board;
	int				retval;
	char				id[16];

	board = spi->dev.platform_data;
	if (!board) {
		dev_dbg(&spi->dev, "no platform_data\n");
		return -ENXIO;
	}

	if (!board->dac_clk) {
		dev_dbg(&spi->dev, "no DAC clk\n");
		return -ENXIO;
	}

	if (IS_ERR(board->dac_clk)) {
		dev_dbg(&spi->dev, "no DAC clk\n");
		return PTR_ERR(board->dac_clk);
	}

	/* Allocate "card" using some unused identifiers. */
	snprintf(id, sizeof id, "at73c213_%d", board->ssc_id);
	retval = snd_card_new(&spi->dev, -1, id, THIS_MODULE,
			      sizeof(struct snd_at73c213), &card);
	if (retval < 0)
		goto out;

	chip = card->private_data;
	chip->spi = spi;
	chip->board = board;

	chip->ssc = ssc_request(board->ssc_id);
	if (IS_ERR(chip->ssc)) {
		dev_dbg(&spi->dev, "could not get ssc%d device\n",
				board->ssc_id);
		retval = PTR_ERR(chip->ssc);
		goto out_card;
	}

	retval = snd_at73c213_dev_init(card, spi);
	if (retval)
		goto out_ssc;

	strcpy(card->driver, "at73c213");
	strcpy(card->shortname, board->shortname);
	sprintf(card->longname, "%s on irq %d", card->shortname, chip->irq);

	retval = snd_card_register(card);
	if (retval)
		goto out_ssc;

	dev_set_drvdata(&spi->dev, card);

	goto out;

out_ssc:
	ssc_free(chip->ssc);
out_card:
	snd_card_free(card);
out:
	return retval;
}